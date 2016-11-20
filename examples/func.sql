CREATE FUNCTION add_one (@input)
AS BEGIN
    SET @Work = @Input + 1
    RETURN @work
END
