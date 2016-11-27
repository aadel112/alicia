READ FILE perf_tests/sp500.csv INTO factstxt;

create table sp(dt text, open real, high real, low real, close real); 
insert into sp select f0, f1, f2, f3, f4 from factstxt;
CREATE INDEX idxsf01 on sp(dt);
ANALYZE;

SELECT
regr_slope( diff, ep),
regr_intercept( diff, ep ),
regr_sxy( diff, ep )
FROM
(
    SELECT 
    CLOSE - OPEN AS DIFF, 
    close as ep
    --CAST(SSTRTOTIME(dt) AS real) AS EP
    FROM sp
)a
;--GROUP BY 1 ORDER BY 1;
