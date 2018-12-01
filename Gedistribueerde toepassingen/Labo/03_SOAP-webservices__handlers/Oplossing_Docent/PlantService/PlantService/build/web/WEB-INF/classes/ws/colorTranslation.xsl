<?xml version="1.0" encoding="UTF-8"?>

<!--
    Document   : colorTranslation.xsl
    Created on : October 26, 2017, 10:21 AM
    Author     : khaluf
    Description:
        Purpose of transformation follows.
-->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0" xmlns:ns2="http://ws/">
<xsl:output method="xml"/>
    <xsl:template match="node()|@*">
        <xsl:copy>
            <xsl:apply-templates select="node()|@*"/>
        </xsl:copy>
    </xsl:template>

    <xsl:template match="kleur/text()[.='yellow']">geel</xsl:template>
    <xsl:template match="kleur/text()[.='blue']">blauw</xsl:template>
    <xsl:template match="kleur/text()[.='orange']">oranje</xsl:template>
</xsl:stylesheet>
