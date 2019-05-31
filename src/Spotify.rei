module Types: {
    module User: {
        [@decco] type id = string;
        [@decco] type t = {
            birthdate: option(string),
            country: option(string),
            display_name: option(string),
            email: option(string),
            href: string,
            id: id,
            product: option(string),
            uri: string,
        };
    };
    module SimplifiedArtist: {
        [@decco] type t = { id: string, name: string, uri: string, };
    };
    module Track: {
        [@decco] type t = {
          artists: array(SimplifiedArtist.t),
          available_markets: array(string),
          disc_number: int,
          duration_ms: int,
          explicit: bool,
          id: string,
          is_playable: option(bool),
          name: string,
          popularity: int,
          preview_url: option(string),
          track_number: int,
          uri: string,
        };
    };
    module PlaylistTrack: {
        [@decco] type t = { is_local: bool, track: Track.t, };
    };
    module Playlist: {
        [@decco] type t = {
            collaborative: bool,
            href: string,
            id: string,
            name: string,
            public: bool,
            snapshot_id: string,
            uri: string,
            owner: User.t,
        };
    };
};
open Types;

module Auth: {
    type scope =
        | UserLibraryRead | UserLibraryModify | PlaylistReadPrivate
        | PlaylistModifyPublic | PlaylistModifyPrivate | PlaylistReadCollaborative
        | UserReadRecentlyPlayed | UserTopRead | UserReadPrivate | UserReadEmail
        | UserReadBirthdate | Streaming | AppRemoteControl | UserModifyPlaybackState
        | UserFollowModify | UserFollowRead;
    let createAuthorizeUrl:
        (~state: string=?, ~forceShowDialog: bool=?, string, string,
        Js.Array.t(scope)) => string;
};

module Playback: {
    type player = Playback.player;
    [@decco] type error = { message: string, };
    [@decco] type initializationError = error;
    [@decco] type authenticationError = error;
    [@decco] type accountError = error;
    [@decco] type playbackError = error;
    [@decco] type webPlaybackPlayer = {
        device_id: string,
    };
    [@decco] type context = {
        uri: option(string),
        metadata: option(Js.Json.t),
    };
    [@decco] type disallows = {
        pausing: bool,
        peeking_next: bool,
        peeking_prev: bool,
        resuming: bool,
        seeking: bool,
        skipping_next: bool,
        skipping_prev: bool,
    };
    [@decco] type trackWindow = {
      current_track: Js.Json.t,
      previous_tracks: array(Js.Json.t),
      next_tracks: array(Js.Json.t),
    };
    [@decco] type repeatMode =
        | NoRepeat
        | RepeatOnce
        | RepeatForever;
    [@decco] type webPlaybackState = {
        context: context,
        disallows: disallows,
        track_window: trackWindow,
        paused: bool,
        position: int,
        repeat_mode: repeatMode,
        shuffle: bool,
    };
    let ensureInitialized: unit => Js.Promise.t(unit);
    let makePlayer: ('a, 'b) => player;
    let connect: player => unit;
    let disconnect: player => unit;
    let onInitializationError:
        (Belt.Result.t(error, Decco.decodeError) => unit, player) => player;
    let onAuthenticationError:
        (Belt.Result.t(error, Decco.decodeError) => unit, player) => player;
    let onAccountError:
        (Belt.Result.t(error, Decco.decodeError) => unit, player) => player;
    let onPlaybackError:
        (Belt.Result.t(error, Decco.decodeError) => unit, player) => player;
    let onReady:
        (Belt.Result.t(webPlaybackPlayer, Decco.decodeError) => unit,
        player) => player;
    let onNotReady:
        (Belt.Result.t(webPlaybackPlayer, Decco.decodeError) => unit,
        player) => player;
    let onPlayerStateChanged:
        (Belt.Result.t(option(webPlaybackState), Decco.decodeError) => unit,
        player) => player;
    let play:
        (~deviceId: string=?, ~positionMs: int=?, string) => Js.Promise.t(unit);
    let playContext:
        (~deviceId: string=?, ~positionMs: int=?, string, string) =>
        Js.Promise.t(unit);
    let playUris:
        (~deviceId: string=?, ~positionMs: int=?, string,
        Js.Array.t(string)) => Js.Promise.t(unit);
};

module Playlists: {
    let tracksMax: int;
    let getTracks:
        (~fields: string=?, ~limit: int=?, ~offset: int=?, ~market: string=?,
        string, string) => Js.Promise.t(Api.page(PlaylistTrack.t));
};

module Users: {
    let me: string => Js.Promise.t(User.t);
    let playlistsMax: int;
    let getPlaylists:
        (~limit: int=?, ~offset: int=?, string, string) =>
        Js.Promise.t(Api.page(Playlist.t));
    let getMyPlaylists:
        (~limit: int=?, ~offset: int=?, string) =>
        Js.Promise.t(Api.page(Playlist.t));
};
