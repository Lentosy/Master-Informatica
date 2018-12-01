<?xml version="1.0"?>

<!--
    Document   : wijken_gesorteerd_op_volgnummer.xsl
    Created on : December 1, 2018, 1:37 PM
    Author     : counterpoint
    Description:
        Lees het vervolg van het artikel en gebruik een xsl-element key) om alle straten uit sector A20 uit te schrijven met een XSLT. 
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    <xsl:template match='/root'>
        <sector>
            <naam>A20</naam>
            <xsl:key match='element' use='sector' name='straten-per-sector'/>
            <xsl:for-each select="key('straten-per-sector', 'A20')">
                <straat>
                    <xsl:value-of select='straatnaam'/>
                </straat>
            </xsl:for-each>
        </sector>
    </xsl:template>
</xsl:stylesheet>
