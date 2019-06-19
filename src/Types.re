exception NoBody(Superagent.result);
exception UnrecognizedResponseFormat(Decco.decodeError);

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
        id: string,
        name: string,
        uri: string,
    };
};

module SimplifiedAlbum = {
    [@decco]
    type t = {
        artists: array(SimplifiedArtist.t),
        available_markets: array(string),
        id: string,
        name: string,
        release_date: string,
        uri: string,
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
        id: string,
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
