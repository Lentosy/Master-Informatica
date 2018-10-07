<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    
    <xsl:template match="/root">
            <wijken>
                <xsl:for-each select="element">
                    <xsl:sort select="wijkNr" />
                    <wijk>
                        <xsl:attribute name="nr">
                            <xsl:value-of select="wijkNr"/>
                        </xsl:attribute>
                        <naam>
                            <xsl:value-of select="wijknaam"/>
                        </naam>
                    </wijk>  
                </xsl:for-each>
            </wijken>
    </xsl:template>

</xsl:stylesheet>
