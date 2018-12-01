<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>

    <xsl:template match="/">
        <sector>
            <naam>A20</naam>
            <xsl:key name="stratenPerSector" match="root/element" use="sector" />
            <xsl:for-each select="key('stratenPerSector', 'A20')"> 
                <straat>
                    <xsl:value-of select="straatnaam"/>
                </straat>
            </xsl:for-each>
        </sector>  
    </xsl:template>
</xsl:stylesheet>
