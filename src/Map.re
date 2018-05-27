/* State declaration */
type state = {node: ref(option(Dom.element))};

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Map");

let setRef = (theRef, {ReasonReact.state}) =>
  state.node := Js.Nullable.toOption(theRef);

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (~greeting, _children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  didMount: self =>
    switch (self.state.node^) {
    | Some(n) => Leaflet.create_map(n) |> ignore
    | None => ()
    },
  initialState: () => {node: ref(None)},
  render: self => <div ref=(self.handle(setRef)) />,
};
