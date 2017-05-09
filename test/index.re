open Js.Promise;

let spotify = Spotify.create [%bs.obj {
    clientId: "clid",
    clientSecret: Js.Undefined.empty,
    redirectUri: "http://www.something.com/"
}];

let authUrl = spotify##createAuthorizeURL [| "user-read-private", "user-read-email" |] "state";

spotify##authorizationCodeGrant "code"
    |> then_ (fun data => {
        Js.log data##expires_in;
        Js.log data##access_token;
        Js.log data##refresh_token;

        spotify##setAccessToken data##access_token;
        spotify##setRefreshToken data##refresh_token;

        resolve ();
    });

spotify##getMe ()
    |> then_ (fun data => {
        let body = data##body;

        Js.log body##display_name;
        Js.log body##href;
        Js.log body##id;
        Js.log body##uri;

        resolve ();
    });

let gupOpts = [%bs.obj { limit: Js.undefined, offset: Js.undefined }];
spotify##getUserPlaylists "user_id" gupOpts
    |> then_ (fun data => {
        data##body##items
            |> Js.Array.forEach (fun playlist => {
                Js.log playlist##collaborative;
                Js.log playlist##href;
                Js.log playlist##id;
                Js.log playlist##name;
                Js.log playlist##public;
                Js.log playlist##snapshot_id;
                Js.log playlist##uri;
            });

        resolve ();
    });

let gptOpts = [%bs.obj { fields: Js.undefined, limit: Js.undefined, offset: Js.undefined }];
spotify##getPlaylistTracks "user_id" "playlist_id" gptOpts
    |> then_ (fun data => {
        data##body##items
            |> Js.Array.forEach (fun track => {
                let track = track##track;

                track##artists
                    |> Js.Array.forEach (fun (artist:Js.t Spotify.simplifiedArtists) => {
                        Js.log artist##id;
                        Js.log artist##name;
                        Js.log artist##uri;
                    });

                Js.log track##available_markets;
                Js.log track##disc_number;
                Js.log track##duration_ms;
                Js.log track##explicit;
                Js.log track##id;
                Js.log track##is_playable;
                Js.log track##name;
                Js.log track##popularity;
                Js.log track##preview_url;
                Js.log track##track_number;
                Js.log track##uri;
            });

        resolve ();
    });

Js.log Spotify.maxPageSizePlaylists;