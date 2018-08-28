ReactDOMRe.renderToElementWithId(<Root />, "container");

/* Users.me(token)
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
    |> PromiseEx.map(() => Js.log("started")); */