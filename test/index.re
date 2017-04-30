let spotify = Spotify.create [%bs.obj {
    clientId: "clid",
    clientSecret: Js.Undefined.empty,
    redirectUri: "http://www.something.com/"
}];

let authUrl = spotify##createAuthorizeURL [| "user-read-private", "user-read-email" |] "state";

spotify##authorizationCodeGrant "code"
    |> Js.Promise.then_ (fun data => {
        Js.log data##expires_in;
        Js.log data##access_token;
        Js.log data##refresh_token;

        spotify##setAccessToken data##access_token;
        spotify##setRefreshToken data##refresh_token;

        Js.Promise.resolve ();
    });

spotify##getMe ()
    |> Js.Promise.then_ (fun data => {
        let body = data##body;

        Js.log body##display_name;
        Js.log body##href;
        Js.log body##id;
        Js.log body##uri;

        Js.Promise.resolve ();
    });

spotify##getUserPlaylists "user_id"
    |> Js.Promise.then_ (fun data => {
        let body = data##body;

        body##items
            |> Js.Array.forEach (fun playlist => {
                Js.log playlist##collaborative;
                Js.log playlist##href;
                Js.log playlist##id;
                Js.log playlist##name;
                Js.log playlist##public;
                Js.log playlist##snapshot_id;
                Js.log playlist##tracks;
                Js.log playlist##uri;
            });

        Js.Promise.resolve ();
    });