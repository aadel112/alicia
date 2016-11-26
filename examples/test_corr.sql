CREATE TABLE test(
    v1 real,
    v2 real
);

INSERT INTO test VALUES ( 10, 2 );
INSERT INTO test VALUES ( 21, 74 );
INSERT INTO test VALUES ( 11, 94 );
INSERT INTO test VALUES ( 16, 23 );
INSERT INTO test VALUES ( 11, 20 );

SELECT CORR( v1, v2 ) FROM test;

SELECT VAR_POP(v1) FROM test;
