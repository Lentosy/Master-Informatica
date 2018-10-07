<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    
    <xsl:key name="stadsdelen-in-gent" match="root/element" use="stadsdeel" />
    <xsl:template match="/root">
        <stadsdelen>
            <xsl:for-each select="element[count(. | key('stadsdelen-in-gent', stadsdeel)[1]) = 1 ]">
                <xsl:sort select="stadsdeel"/>
                <stadsdeel>
                    <xsl:value-of select="stadsdeel" />
                </stadsdeel>
            </xsl:for-each>

        </stadsdelen>
    </xsl:template> 
</xsl:stylesheet>
