open ReDom;
open ReactLib;

type state =
    | Initializing
    | Loaded(string)
    | Redirecting;

type action =
    | SetRedirecting
    | SetLoaded(string);

[@decco] type config = { clientId: string };
[@bs.module] external config : Js.Json.t = "../../../../config.json";
let clientId = switch (config_decode(config)) {
    | Ok({ clientId }) => clientId
    | _ => failwith("Invalid config")
};

let component = ReasonReact.reducerComponent("Root");
let make = (_) => {
    {
        ...component,

        render: ({ state }) =>
            switch state {
                | Initializing => <div>(s2e("loading..."))</div>
                | Redirecting => <div>(s2e("redirecting..."))</div>
                | Loaded(token) => <TestTool token />
            },

        initialState: (_) => Initializing,

        reducer: (action, _) =>
            switch action {
                | SetRedirecting => ReasonReact.Update(Redirecting)
                | SetLoaded(token) => ReasonReact.Update(Loaded(token))
            },

        didMount: ({ send }) =>
            switch (OAuth.getAccessTokenFromHash()) {
                | Some(token) => send(SetLoaded(token))
                | None => {
                    Auth.createAuthorizeUrl(
                        clientId, "http://localhost:54380/",
                        [| Auth.UserModifyPlaybackState, Auth.Streaming |]
                    )
                    |> Location.setHref;

                    send(SetRedirecting);
                }
            }
    };
};