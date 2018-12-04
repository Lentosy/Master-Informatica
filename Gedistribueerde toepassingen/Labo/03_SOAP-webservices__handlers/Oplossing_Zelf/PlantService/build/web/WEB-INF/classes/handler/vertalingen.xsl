<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : vertalingen.xsl
    Created on : December 1, 2018, 6:25 PM
    Author     : counterpoint
    Description:
        Purpose of transformation follows.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>

    <!-- TODO customize transformation rules 
         syntax recommendation http://www.w3.org/TR/xslt 
    -->
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/> 
        </xsl:copy>
    </xsl:template>
    
    <xsl:template match="kleur/text()[.='yellow']">geel</xsl:template>
    <xsl:template match="kleur/text()[.='red']">rood</xsl:template>
    <xsl:template match="kleur/text()[.='green']">groen</xsl:template>

</xsl:stylesheet>
