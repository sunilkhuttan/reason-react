/* This is the basic component. */
let component = ReasonReact.statelessComponent("Greet");

/* Your familiar handleClick from ReactJS. This mandatorily takes the payload,
   then the `self` record, which contains state (none here), `handle`, `reduce`
   and other utilities */
let handleClick = (_event, _self) => Js.log("clicked!");
let space = " ";

/* `make` is the function that mandatorily takes `children` (if you want to use
   `JSX). `message` is a named argument, which simulates ReactJS props. Usage:

   `<Page message="hello" />`

   Which desugars to

   `ReasonReact.element(Page.make(~message="hello", [||]))` */
let make = (~greet, ~firstname, ~lastname , _children) => {
  ...component,
  render: self =>
    /*<div onClick=(self.handle(handleClick))>     */
    <div onClick=(self.handle(handleClick))> 
      (ReasonReact.string(firstname)) (ReasonReact.string(" ")) (ReasonReact.string(lastname))   <br />
      (ReasonReact.string(greet))
      (ReasonReact.string(string_of_int(10)))  
      <button>(ReasonReact.string("Click me!")) </button>
    </div>,
};
