module Access: {
    type o;
    type x;
    /** Labelled types included for better error messages */
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
    let all: scope(o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o,o);

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
        (~limitScope: scope('q,'w,'e,'r,'e,'t,'y,'u,'i,'o,'p,'a,'s,'d,'f,'g,'h,'j)=?,
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
        [@decco]
        type t = {
            id: option(string),
            name: string,
            uri: option(string),
        };
    };
    module SimplifiedAlbum: {
        [@decco]
        type t = {
            artists: array(SimplifiedArtist.t),
            available_markets: array(string),
            id: option(string),
            name: string,
            release_date: option(string),
            uri: option(string),
        };
    };
    module Track: {
        [@decco] type t = {
            album: SimplifiedAlbum.t,
            artists: array(SimplifiedArtist.t),
            available_markets: array(string),
            disc_number: int,
            duration_ms: int,
            explicit: bool,
            id: option(string),
            is_playable: option(bool),
            name: string,
            popularity: int,
            preview_url: option(string),
            track_number: int,
            uri: string,
        };
    };
    module PlaylistTrack: {
        [@decco]
        type t = {
            added_at: string,
            is_local: bool,
            track: Track.t,
        };
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
    [@decco]
    type tokens = {
        access_token: string,
        refresh_token: option(string),
        expires_in: int
    };
    let createAuthorizeUrl:
        (~state: string=?, ~forceShowDialog: bool=?, string, string,
          Access.scope(_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_,_),
          [< `Code | `Token ])
        => string;
    let getTokensFromCode: (string, string, string, string) => Js.Promise.t(tokens);
    let refreshAccessToken: (string, string, string) => Js.Promise.t(tokens);
};

module Api: {
    [@decco]
    type page('a) = {
        href: string,
        items: array('a),
        limit: int,
        next: option(string),
        offset: int,
        previous: option(string),
        total: int,
    };
    let buildGet: (token(_), string) => Superagent.request(Superagent.get);
    let buildPut: (token(_), string) => Superagent.request(Superagent.put);
    let setOptionalQueryParam:
        (Js.Dict.key, option(string), Superagent.request('a))
        => Superagent.request('a);
    let setOptionalParam:
        (Js.Dict.key, option(Js.Json.t), Superagent.request(Superagent.acceptsBody))
        => Superagent.request(Superagent.acceptsBody);
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
