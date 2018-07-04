/* type state = {
    show: bool,
    cities : list,
};

type action = 
  | CitiesFetched(cities);

let component = ReasonReact.reducerComponent("CityInfo");

let str = ReasonReact.stringToElement;

let make = (_children) => {
  ...component,
  initialState: () => {
    cities: None
  },
  reducer: (action, state) => {
    switch action {
    | CitiesFetched(cities) => ReasonReact.Update({
      cities: Some(cities)
    })
    }
  },
  didMount: (_) => {
    Js.Promise.(
      Axios.get("http://localhost:55680/api/cities")
      |> then_((response) => resolve(Js.log(response##data)))
      |> catch((error) => resolve(Js.log(error)))
      |> ignore
    );
    ReasonReact.NoUpdate
  },
  render: (self) => <div> </div>
};  */

let component = ReasonReact.statelessComponent("CityInformation");

let str = ReasonReact.stringToElement;

let make = (_children) => {
  ...component,
  /* didMount: (self) =>
    Js.Promise.(
      /* Axios.get("http://localhost:55680/api/cities")
      |> then_((response) => resolve(Js.log(response##data)))
      |> catch((error) => resolve(Js.log(error))) */
    ), */

    /* didMount: (self) => 
    Js.Promise.(
      Axios.get("http://localhost:55680/api/cities/singlecity")
      |> then_((response) => resolve(Js.log(response##data)))
    ), */
  render: (_self) => <div> (str("CityInformation")) </div>
};
