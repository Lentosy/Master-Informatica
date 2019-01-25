<?xml version="1.0"?>

<!--
    Document   : wijken_gesorteerd_op_volgnummer.xsl
    Created on : December 1, 2018, 1:37 PM
    Author     : counterpoint
    Description:
        Lees het artikel (http://www.jenitennison.com/xslt/grouping/muenchian.html) Grouping Using the Muenchian Method en gebruik de eerst beschreven methode om een XML-bestand met alle wijken te maken. 
        Dit is de methode die nog geen gebruik maakt van keys, maar wel van de lange asnamen.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    <xsl:template match='/root'>
        <overzicht>
            <wijken>
                <xsl:variable select='element[not(wijkNr = preceding-sibling::element/wijkNr)]' name='wijken' />
                <xsl:for-each select="$wijken">
                    <xsl:sort select='wijkNr' data-type='number' order='ascending'/>
                    <wijk>
                        <xsl:attribute name='nr'>
                            <xsl:value-of select='wijkNr'/>
                        </xsl:attribute>
                        <naam>
                            <xsl:value-of select='wijknaam'/>
                        </naam>
                    </wijk>              
                </xsl:for-each>
            </wijken>
        </overzicht>
    </xsl:template>
</xsl:stylesheet>
