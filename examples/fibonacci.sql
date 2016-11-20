CREATE FUNCTION fibonacci(@n)
AS BEGIN
    CASE WHEN @n == 1 OR @n == 0 THEN
        RETURN 1
    ELSE
        RETURN fibonacci(@n-2)+fibonacci(@n-1)
    END
END
