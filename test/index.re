/* open Js.Promise;

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

Js.log Spotify.maxPageSizePlaylists; */

open Belt.Result;
open Js.Promise;
open ReDomSuite;

[@decco] type config = { clientId: string };
[@bs.module] external config : Js.Json.t = "../../../config.json";
let clientId = switch (config_decode(config)) {
    | Ok({ clientId }) => clientId
    | _ => failwith("Invalid config")
};

let token = switch (OAuth.getAccessTokenFromHash()) {
    | Some(token) => token
    | None => {
        Auth.createAuthorizeUrl(clientId, "http://localhost:54380/", [| Auth.UserModifyPlaybackState, Auth.Streaming |])
            |> Location.setHref(ReDom.location);
        failwith("Redirecting");
    }
};

Users.me(token)
    |> then_(({ Types.User.display_name, id }) => {
        switch display_name {
            | Some(name) => Js.log2("hey it's", name)
            | None => Js.log("noname")
        };

        Users.getPlaylists(~limit=1, token, id);
    })
    |> then_(({ Api.items, offset, total }) => {
        Js.log2(offset, total);
        items
            |> Js.Array.map(({ Types.Playlist.id, name }) => {
                Js.log2(id, name);
                Playlists.getTracks(~limit=10, token, id);
            })
            |> Js.Promise.all;
    })
    |> PromiseEx.map(Js.Array.map(({ Api.items, offset, total }) => {
        Js.log2(offset, total);
        items
            |> Js.Array.map(({ Types.PlaylistTrack.track }) => {
                Js.log3(track.artists[0].name, {j|–|j}, track.name);
            });

        ();
    }))
    |> PromiseEx.thenResolve()
    |> catch(err => {
        Js.log2("err", err);
        resolve();
    });

Playback.init()
    |> PromiseEx.map(() => Js.log("started"));