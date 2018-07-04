/* State declaration */
type state = {
  count: int,
  show: bool,
  showDetails: bool,
  firstname: string,
  lastname: string,
  email: string,
  mobile: string
};

/* Action declaration */
type action =
  | Click
  | Toggle
  | ToggleDetails;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Example");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~greeting, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,

  initialState: () => {count: 0, show: true, showDetails: true, firstname: "Sunil", 
  lastname: "K", email: "sunil.k@example.com", mobile: "09999999448" },

  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Click => ReasonReact.Update({...state, count: state.count + 1})
    | Toggle => ReasonReact.Update({...state, show: ! state.show})
    | ToggleDetails => ReasonReact.Update({...state, showDetails: !state.showDetails})
    },

  render: self => {
    let message =
      "You've clicked this " ++ string_of_int(self.state.count) ++ " times(s)";
    <div>
      /* <Component1 message="Test!" > </Component1>
      <button onClick=(_event => self.send(Click))>
        (ReasonReact.string(message))
      </button>
      <button onClick=(_event => self.send(Toggle))>
        (ReasonReact.string("Toggle greeting"))
      </button>
      (self.state.show ? ReasonReact.string(greeting) : ReasonReact.null) */
      <div >
        <button onClick=(_event => self.send(ToggleDetails))>
          (ReasonReact.string("Show/Hide My Details"))
        </button>          
          (self.state.showDetails ? 
          <div>
            <lable>(ReasonReact.string("First Name : "))</lable> (ReasonReact.string(self.state.firstname)) <br/>
            <lable>(ReasonReact.string("Last Name : "))</lable> (ReasonReact.string(self.state.lastname)) <br/>
            <lable>(ReasonReact.string("Email : "))</lable> (ReasonReact.string(self.state.email)) <br/>
            <lable>(ReasonReact.string("Mobile : "))</lable> (ReasonReact.string(self.state.mobile)) <br/>
          </div> : ReasonReact.null)
      </div>
    </div>;
  },
};
