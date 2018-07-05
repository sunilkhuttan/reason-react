/* The new stdlib additions */
/* This is the example of cities array returned from api. Create an end point to return this array and upsate the get URI
    [
        {
            "id": 2,
            "name": "London",
            "description": "Biggest city in England."
        },
        {
            "id": 1,
            "name": "New York City",
            "description": "The one with that big park."
        },
        {
            "id": 3,
            "name": "Paris",
            "description": "The one with that big tower."
        }
    ]
*/
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
      <div id="city-div">
        <h1> (ReasonReact.string("Cities")) </h1>
        <a href="#">
          (ReasonReact.string("Home"))
        </a>
        <ul className="city-list">
          (
            Array.map(cities, city =>
            <li className="city-list-item" key=city.name>
                (ReasonReact.string("Name : ")) (ReasonReact.string(city.name)) <br></br>
                (ReasonReact.string("Description : ")) (ReasonReact.string(city.description))<br></br>
            </li> 
            )
            |> ReasonReact.array 
          )
        </ul>

      </div>
    },
};
