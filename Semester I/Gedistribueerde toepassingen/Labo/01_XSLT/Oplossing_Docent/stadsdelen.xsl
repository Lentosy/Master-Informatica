<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>

    <xsl:template match="/">
        <stadsdelen>    
            <xsl:apply-templates select="root"/>
        </stadsdelen>
    </xsl:template>
    <xsl:key name="straat-by-stadsdeel" match="root/element" 
             use="stadsdeel"/>
    <xsl:template match="root">
        <xsl:for-each select="element[generate-id() = generate-id(key('straat-by-stadsdeel',stadsdeel)[1])]">
            <xsl:sort select="stadsdeel"/> 
            <stadsdeel>
                <naam>
                    <xsl:value-of select="stadsdeel"/>                     
                </naam>                             
            </stadsdeel>                 
        </xsl:for-each>
    </xsl:template>
</xsl:stylesheet>
