let s2e = ReasonReact.string;

let getOption = fun
    | Some(v) => v
    | None => failwith("Expected Some, got None");

let noopSubmit = (e) => ReactEvent.Form.preventDefault(e);

let width = (w) => ReactDOMRe.Style.make(~width=w, ());
