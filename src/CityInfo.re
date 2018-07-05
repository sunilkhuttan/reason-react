/* The new stdlib additions */
open Belt;

type city = {
    id: int,
    name: string,
    description: string
};

type state =
  | Loading
  | Error
  | Loaded(array(city));

type action =
  | CitiesFetch
  | CitiesFetched(array(city))
  | CitiesFailedToFetch;

module Decode = {
    let decodedCity = json : city  =>
        Json.Decode.{
        id: json |> field("id", int),
        name: json |> field("name", string),
        description: json |> field("description", string)
    };

    let cities = json : array(city) =>
    Json.Decode.(
        json |> array(decodedCity) |> Array.map(_, city => city)
    );
};

let component = ReasonReact.reducerComponent("CityInfo");

let make = _children => {
  ...component,
  initialState: _state => Loading,
  reducer: (action, _state) =>
    switch (action) {
    | CitiesFetch =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Fetch.fetch("http://localhost:55680/api/cities")
              |> then_(Fetch.Response.json)
              |> then_(json =>
                   json
                   |> Decode.cities
                   |> (cities => self.send(CitiesFetched(cities)))
                   |> resolve
                 )
              |> catch(_err =>
                   Js.Promise.resolve(self.send(CitiesFailedToFetch))
                 )
              |> ignore
            )
        ),
      )
    | CitiesFetched(cities) => ReasonReact.Update(Loaded(cities))
    | CitiesFailedToFetch => ReasonReact.Update(Error)
    },
  didMount: self => self.send(CitiesFetch),
  render: self =>
    switch (self.state) {
    | Error => <div> (ReasonReact.string("An error occurred!")) </div>
    | Loading => <div> (ReasonReact.string("Loading...")) </div>
    | Loaded(cities) =>
      <div>
        <h1> (ReasonReact.string("Cities")) </h1>
        <p> (ReasonReact.string("Source: ")) </p>
        <a href="https://city.ceo">
          (ReasonReact.string("https://city.ceo"))
        </a>
        <ul>
          (
            Array.map(cities, city =>
              <li key=city.name> (ReasonReact.string(city.name)) </li> 
            )
            |> ReasonReact.array 
          )
        </ul>
      </div>
    },
};
