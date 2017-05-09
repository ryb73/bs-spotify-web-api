let maxPageSizePlaylists = 50;
let maxPageSizeTracks = 100;

class type codeGrant = {
    pub expires_in : string;
    pub access_token : string;
    pub refresh_token : string;
};

class type playlist = {
    pub collaborative : Js.boolean;
    pub href : string;
    pub id : string;
    pub name : string;
    pub public : Js.boolean;
    pub snapshot_id	: string;
    pub uri : string;
};

class type simplifiedArtists = {
    pub id : string;
    pub name : string;
    pub uri : string;
};

class type track = {
    pub artists : array (Js.t simplifiedArtists);
    pub available_markets : array string;
    pub disc_number : int;
    pub duration_ms : int;
    pub explicit : Js.boolean;
    pub id : string;
    pub is_playable : Js.undefined Js.boolean;
    pub name : string;
    pub popularity : int;
    pub preview_url : Js.null string;
    pub track_number : int;
    pub uri : string;
};

class type playlistTrack = {
    pub is_local : Js.boolean;
    pub track : Js.t track;
};

class type page 'a = {
    pub href : string;
    pub items : array (Js.t 'a);
    pub limit : int;
    pub next : string;
    pub offset : int;
    pub previous : string;
    pub total : int;
};

class type user = {
    pub display_name : string;
    pub href : string;
    pub id : string;
    pub uri : string;
};

class type body 'a = {
    pub body : Js.t 'a;
};

type apiPromise 'a = Js.Promise.t (Js.t (body 'a));

type getUserPlaylistsOptions = [%bs.obj: {.
    limit: Js.undefined int,
    offset: Js.undefined int
}];

type getPlaylistTracksOptions = [%bs.obj: {.
    limit: Js.undefined int,
    offset: Js.undefined int,
    fields: Js.undefined string
}];

class type t = {
    pub createAuthorizeURL : array string => string => string;
    pub authorizationCodeGrant : string => Js.Promise.t (Js.t codeGrant);
    pub setAccessToken : string => unit;
    pub setRefreshToken : string => unit;
    pub getMe : unit => apiPromise user;
    pub getUserPlaylists : string => getUserPlaylistsOptions => apiPromise (page playlist);
    pub getPlaylistTracks : string => string => getPlaylistTracksOptions => apiPromise (page playlistTrack);
} [@bs];

type options = [%bs.obj: {.
    clientId : string,
    clientSecret : Js.undefined string,
    redirectUri : string
}];

external create : options => Js.t t = "spotify-web-api-node" [@@bs.new] [@@bs.module];