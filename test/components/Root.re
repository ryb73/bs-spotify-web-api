open React;
open ReDom;
open ReactLib;
open Spotify;

[@decco] type config = { clientId: string };
[@bs.module] external config : Js.Json.t = "../../../../config.json";
let clientId = switch (config_decode(config)) {
    | Ok({ clientId }) => clientId
    | _ => failwith("Invalid config")
};

let scope = Access.(scope
// |> withUserLibraryRead
// |> withUserLibraryModify
// |> withPlaylistReadPrivate
// |> withPlaylistModifyPublic
// |> withPlaylistModifyPrivate
// |> withPlaylistReadCollaborative
// |> withUserReadRecentlyPlayed
// |> withUserTopRead
|> withUserReadPrivate
|> withUserReadEmail
|> withUserReadBirthdate
// |> withUserReadPlaybackState
// |> withUserReadCurrentlyPlaying
|> withStreaming
// |> withAppRemoteControl
|> withUserModifyPlaybackState
// |> withUserFollowModify
// |> withUserFollowRead
);

[@react.component]
let make = () => {
    let (redirecting, setRedirecting) = useState(_ => false);
    let (token, setToken) = useState(_ => None);

    useEffect0(() => {
        switch (OAuth.getAccessTokenFromHash()) {
            | Some(token) =>
                setToken(_ => Some(Access.token(~limitScope=scope, token)))
            | None => {
                Auth.createAuthorizeUrl(
                    clientId, "http://localhost:54380/",
                    scope,
                    `Token
                )
                |> Location.setHref;

                setRedirecting(_ => true);
            }
        };
        None;
    });

    switch (redirecting, token) {
        | (false, None) => <div>(s2e("loading..."))</div>
        | (true, _) => <div>(s2e("redirecting..."))</div>
        | (false, Some(token)) => <TestTool token />
    }
};