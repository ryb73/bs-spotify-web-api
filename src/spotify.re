class type codeGrant = {
    pub expires_in : string;
    pub access_token : string;
    pub refresh_token : string;
};

class type tracks = {
    pub id : string;
};

class type playlist = {
    pub collaborative : Js.boolean;
    pub href : string;
    pub id : string;
    pub name : string;
    pub public : Js.boolean;
    pub snapshot_id	: string;
    pub tracks : Js.t tracks;
    pub uri : string;
};

class type playlists = {
    pub href : string;
    pub items : array (Js.t playlist);
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

class type t = {
    pub createAuthorizeURL : array string => string => string;
    pub authorizationCodeGrant : string => Js.Promise.t (Js.t codeGrant);
    pub setAccessToken : string => unit;
    pub setRefreshToken : string => unit;
    pub getMe : unit => apiPromise user;
    pub getUserPlaylists : string => apiPromise playlists;
} [@bs];

type options = [%bs.obj: {.
    clientId : string,
    clientSecret : Js.undefined string,
    redirectUri : string
}];

external create : options => Js.t t = "spotify-web-api-node" [@@bs.new] [@@bs.module];