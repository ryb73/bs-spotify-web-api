let s2e = ReasonReact.string;

let getOption = Belt.Option.getExn;

let noopSubmit = (e) => ReactEvent.Form.preventDefault(e);

let width = (w) => ReactDOMRe.Style.make(~width=w, ());
