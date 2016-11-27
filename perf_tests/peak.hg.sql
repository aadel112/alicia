READ FILE perf_tests/seq.tbl INTO seqtxt;
READ FILE perf_tests/peak.data.hg INTO factstxt;

create table secs ( epoch int );
insert into secs select * from seqtxt;
DROP TABLE seqtxt;
create index idxs01 on secs(epoch);
create table facts ( st int, en int );
insert into facts select f0, f1 from factstxt;
CREATE INDEX idxsf01 on facts(st,en);
DROP TABLE factstxt;
ANALYZE;

CREATE TABLE peaks ( ep int, cnt int );

--INSERT INTO peaks 
SELECT stimestamp(ep), m
FROM
(
SELECT (ep/3600*3600) || '' as ep, max(c) as m
FROM 
( 
    SELECT s.epoch as ep, count(*) as c
    From secs s, facts f 
    where s.epoch >= f.st and s.epoch <= f.en
    group by 1
) a 
GROUP BY 1 
) b
ORDER BY 1;
--WRITE FILE peaks.csv FROM peaks;

