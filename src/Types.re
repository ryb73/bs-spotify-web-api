exception NoBody(Superagent.result);
exception UnrecognizedResponseFormat(Decco.decodeError, Js.Json.t);

module User = {
    [@decco] type id = string;

    [@decco]
    type t = {
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

module SimplifiedArtist = {
    [@decco]
    type t = {
        id: option(string),
        name: string,
        uri: option(string),
    };
};

module SimplifiedAlbum = {
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

module Track = {
    [@decco]
    type t = {
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

module PlaylistTrack = {
    [@decco]
    type t = {
        added_at: string,
        is_local: bool,
        track: Track.t,
    };
};

module Playlist = {
    [@decco]
    type t = {
        collaborative: bool,
        href: string,
        id: string,
        name: string,
        public: bool,
        snapshot_id: string,
        uri: string,
        owner: User.t
    };
};
