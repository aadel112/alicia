CREATE FUNCTION StripWWWandCom (@input)
AS BEGIN
    DECLARE @Work
    SET @Work = @Input
    SET @Work = REPLACE(@Work, 'www.', '')
    SET @Work = REPLACE(@Work, '.com', '')

    RETURN @work
END
