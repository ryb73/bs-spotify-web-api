module Access: {
    type o;
    type x;
    type userLibraryRead = o;
    type userLibraryModify = o;
    type playlistReadPrivate = o;
    type playlistModifyPublic = o;
    type playlistModifyPrivate = o;
    type playlistReadCollaborative = o;
    type userReadRecentlyPlayed = o;
    type userTopRead = o;
    type userReadPrivate = o;
    type userReadEmail = o;
    type userReadBirthdate = o;
    type userReadPlaybackState = o;
    type userReadCurrentlyPlaying = o;
    type streaming = o;
    type appRemoteControl = o;
    type userModifyPlaybackState = o;
    type userFollowModify = o;
    type userFollowRead = o;

    type scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_);
    let scope: scope(x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x);

    let withUserLibraryRead:
        scope(_,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope(o,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserLibraryModify:
        scope('s1,_,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,o,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withPlaylistReadPrivate:
        scope('s1,'s2,_,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,o,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withPlaylistModifyPublic:
        scope('s1,'s2,'s3,_,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,o,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withPlaylistModifyPrivate:
        scope('s1,'s2,'s3,'s4,_,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,o,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withPlaylistReadCollaborative:
        scope('s1,'s2,'s3,'s4,'s4,_,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s4,o,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserReadRecentlyPlayed:
        scope('s1,'s2,'s3,'s4,'s4,'s5,_,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s4,'s5,o,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserTopRead:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,_,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,o,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserReadPrivate:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,_,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,o,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserReadEmail:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,_,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,o,'s11,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserReadBirthdate:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,_,'s12,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,o,'s12,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserReadPlaybackState:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,_,'s13,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,o,'s13,'s14,'s15,'s16,'s17,'s18);
    let withUserReadCurrentlyPlaying:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,_,'s14,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,o,'s14,'s15,'s16,'s17,'s18);
    let withStreaming:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,_,'s15,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,o,'s15,'s16,'s17,'s18);
    let withAppRemoteControl:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,_,'s16,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,o,'s16,'s17,'s18);
    let withUserModifyPlaybackState:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,_,'s17,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,o,'s17,'s18);
    let withUserFollowModify:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,_,'s18) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,o,'s18);
    let withUserFollowRead:
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,_) =>
        scope('s1,'s2,'s3,'s4,'s5,'s6,'s7,'s8,'s9,'s10,'s11,'s12,'s13,'s14,'s15,'s16,'s17,o);

    type token('a);
    let token:
        (~limitScope: scope('q,'w,'e,'r,'e,'t,'y,'u,'i,'o,'p,'a,'s,'d,'f,'g,'h,'j),
          string)
          => token(scope('q,'w,'e,'r,'e,'t,'y,'u,'i,'o,'p,'a,'s,'d,'f,'g,'h,'j));
};
open Access;

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
    let createAuthorizeUrl:
        (~state: string=?, ~forceShowDialog: bool=?, string, string,
          Access.scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_),
          [< `Code | `Token ])
        => string;
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
    /** (token, playerName) => player */
    let makePlayer:
        (token(scope(_,_,_,_,_,_,_,_,userReadPrivate,userReadEmail,userReadBirthdate,_,_,streaming,_,_,_,_)),
         string)
        => player;
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
        (~deviceId: string=?, ~positionMs: int=?,
          token(scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,userModifyPlaybackState,_,_)))
        => Js.Promise.t(unit);
    let playContext:
        (~deviceId: string=?, ~positionMs: int=?,
          token(scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,userModifyPlaybackState,_,_)),
          string)
        => Js.Promise.t(unit);
    let playUris:
        (~deviceId: string=?, ~positionMs: int=?,
          token(scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,userModifyPlaybackState,_,_)),
          Js.Array.t(string))
        => Js.Promise.t(unit);
};

module Playlists: {
    let tracksMax: int;
    let getTracks:
        (~fields: string=?, ~limit: int=?, ~offset: int=?, ~market: string=?,
          token(_), string)
        => Js.Promise.t(Api.page(PlaylistTrack.t));
};

module Users: {
    // TODO: link scope typing to type of user result?
    let me: token(scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_)) => Js.Promise.t(User.t);
    let playlistsMax: int;
    let getPlaylists:
        (~limit: int=?, ~offset: int=?, token(_), string) =>
        Js.Promise.t(Api.page(Playlist.t));
    let getMyPlaylists:
        (~limit: int=?, ~offset: int=?, token(_)) =>
        Js.Promise.t(Api.page(Playlist.t));
};
