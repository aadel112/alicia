READ FILE perf_tests/sp.data.hg INTO factstxt;

create table sp(dt text, open real, high real, low real, close real); 
insert into sp select f0, f1, f2, f3, f4 from factstxt;
CREATE INDEX idxsf01 on sp(dt);
ANALYZE;

SELECT
regr_slope( diff, close),
regr_intercept( diff, close ),
regr_sxy( diff, close )
    FROM
    (
        SELECT 
        CLOSE - OPEN AS DIFF, 
        close
        FROM sp
    ) a ;
