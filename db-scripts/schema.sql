
-- database already exists

\c :dbname 


-- Pick the one most appropriate for your application
-- CREATE DOMAIN TimePoint AS date ;
create domain TimePoint as timestamp ;
-- create domain TimePoint as timestamp with time zone;

CREATE DOMAIN  String4VarName AS VARCHAR(30) ;
CREATE DOMAIN  String4Info as VARCHAR(200) ;

-- Pick the one most appropriate for your application
--CREATE DOMAIN VarType AS real ;
create domain VarType as double precision ;
-- create domain VarType as int ;


CREATE TYPE DomainType AS ENUM ('discrete', 'real', 'double');



-- Patient data that depend on time
-- Variables within time series (all have the same type)
CREATE TABLE IF NOT EXISTS TimeVar (
    vid serial PRIMARY KEY,     -- serial id for variable
    pid int NOT NULL,           -- pid of process logged
    sysname String4Info,        --- system containing logged variable
    varname String4VarName NOT NULL,     -- variable name
    vardomain DomainType NOT NULL,
    varinfo String4Info NOT NULL
);


CREATE TABLE IF NOT EXISTS LogTable (
    nanosec bigint NOT NULL,		-- nanseconds after second
    vid int NOT NULL,			-- variable id
    varvalue VarType,                       -- variable value
    loginfo String4Info,                    -- extra info
    t interval HOUR TO SECOND (3) NOT NULL,
    PRIMARY KEY (nanosec, vid),
    CONSTRAINT vid_ref FOREIGN KEY(vid) REFERENCES TimeVar(vid)
);

CREATE TABLE IF NOT EXISTS SafetyTable (
    t interval HOUR TO SECOND (3) PRIMARY KEY,
    safety boolean
);

CREATE TABLE IF NOT EXISTS LivenessTable (
    t interval HOUR TO SECOND (3) PRIMARY KEY,
    liveness boolean
);

CREATE TABLE IF NOT EXISTS MinimalDose (
    t interval HOUR TO SECOND (3) PRIMARY KEY,
    min_dose int
);