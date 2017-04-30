let spotify = Spotify.create [%bs.obj {
    clientId: "clid",
    clientSecret: Js.Undefined.empty,
    redirectUri: "http://www.something.com/"
}];

let authUrl = spotify##createAuthorizeURL [| "user-read-private", "user-read-email" |] "state";

let pauth = spotify##authorizationCodeGrant "code";
pauth
    |> Js.Promise.then_ (fun data => {
        Js.log data##expires_in;
        Js.log data##access_token;
        Js.log data##refresh_token;

        spotify##setAccessToken data##access_token;
        spotify##setRefreshToken data##refresh_token;

        Js.Promise.resolve ();
    });