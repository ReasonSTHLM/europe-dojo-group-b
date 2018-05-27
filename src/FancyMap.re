/* State declaration */
type state = {node: ref(option(Dom.element))};

type action = int;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Map");

let setRef = (theRef, {ReasonReact.state}) =>
  state.node := Js.Nullable.toOption(theRef);

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = (_children) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  didMount: self =>
    switch (self.state.node^) {
    | Some(n) => {
      let map = Leaflet.create_map(n, {"center": (0, 0), "zoom": 13});
      let layer = Leaflet.tileLayer("https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png", {
      "maxZoom": 18,
      "minZoom": 1,
      "detectRetina": true,
      });

      Leaflet.Map.addLayer(map, layer) |> ignore;
    }
      
    | None => ()
    },
  reducer: (action:int, state) => ReasonReact.Update(state),
  initialState: () => {node: ref(None)},
  render: self => <div ref=(self.handle(setRef)) />,
};
