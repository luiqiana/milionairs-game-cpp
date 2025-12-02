create table if not exists questions
(
    id    int auto_increment
        primary key,
    level int          not null,
    quest varchar(512) not null,
    ans   varchar(256) not null,
    bad1  varchar(256) not null,
    bad2  varchar(256) not null,
    bad3  varchar(255) not null
);

create table if not exists players
(
    id           int auto_increment
        primary key,
    username     varchar(256) not null,
    wins         int          not null,
    played_games int          not null,
    `5050`       int          not null,
    phone        int          not null,
    publicity    int          not null,
    money        int          not null
);
