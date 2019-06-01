open ReDom;

let s2e = ReasonReact.string;

let getOption = Belt.Option.getExn;

let noopSubmit = (e) => ReactEvent.Form.preventDefault(e);

let width = (w) => ReactDOMRe.Style.make(~width=w, ());

let getTargetValue = (e) =>
    ReactEvent.Form.currentTarget(e)
    |> Obj.magic
    |> Element.fromDom
    |> Input.cast
    |> Belt.Option.getExn
    |> Input.value;
