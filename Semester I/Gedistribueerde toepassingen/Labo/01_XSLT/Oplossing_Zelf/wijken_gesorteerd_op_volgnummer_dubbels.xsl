<?xml version="1.0"?>

<!--
    Document   : wijken_gesorteerd_op_volgnummer.xsl
    Created on : December 1, 2018, 1:37 PM
    Author     : counterpoint
    Description:
        Schrijf een XSLT die op basis van het stratenbestand alle wijken volgens oplopend volgnummer uitschrijft. In de eerste versie mag je de "dubbels" behouden. 
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    
    <xsl:template match='/root'>
        <overzicht>
            <wijken>
                <xsl:variable name='wijken' select='element'/> 
                <xsl:apply-templates select='$wijken'>
                    <xsl:sort select='wijkNr'/>
                </xsl:apply-templates>    
            </wijken>
        </overzicht>
    </xsl:template>
    
    <xsl:template match='element'>
        <wijk>
            <xsl:attribute name="nr">
                <xsl:value-of select="wijkNr"/>
            </xsl:attribute>
            <naam>
                <xsl:value-of select="wijknaam"/>
            </naam>
        </wijk>   
    </xsl:template>
    
</xsl:stylesheet>
