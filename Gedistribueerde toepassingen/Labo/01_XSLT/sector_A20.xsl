<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    
    <xsl:variable name='sector'>A20</xsl:variable>
    <xsl:key name='straten-per-sector' match="root/element" use="sector"/>
    <xsl:template match="/root">
        <sector>
            <naam>
                <xsl:value-of select="$sector"/>
            </naam>
            <xsl:for-each select="key('straten-per-sector', $sector)">
                <xsl:sort select="straatnaam" data-type="number" order="ascending"/>
                <straat>
                    <xsl:value-of select="straatnaam"/>
                </straat>
            </xsl:for-each>
        </sector>
    </xsl:template>
  
</xsl:stylesheet>
