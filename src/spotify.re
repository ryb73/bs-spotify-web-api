class type data = {
    pub expires_in : string;
    pub access_token : string;
    pub refresh_token : string;
};

class type t = {
    pub createAuthorizeURL : array string => string => string;
    pub authorizationCodeGrant : string => Js.Promise.t (Js.t data);
    pub setAccessToken : string => unit;
    pub setRefreshToken : string => unit;
} [@bs];

type options = [%bs.obj: {.
    clientId : string,
    clientSecret : Js.undefined string,
    redirectUri : string
}];

external create : options => Js.t t = "spotify-web-api-node" [@@bs.new] [@@bs.module];