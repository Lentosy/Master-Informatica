<?xml version="1.0"?>

<!--
    Document   : wijken_gesorteerd_op_volgnummer.xsl
    Created on : December 1, 2018, 1:37 PM
    Author     : counterpoint
    Description:
        Gebruik de tweede methode "The Muenchian Method" (met het xsl-element key) om een XSLT te maken die alle stadsdelen gesorteerd uitschrijft (zonder dubbels). 
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    
    
    <xsl:key match='element' use='stadsdeel' name='stadsdelen'/>
    <xsl:template match='/root'>
        <stadsdelen>
            <xsl:apply-templates select='element[count(. | key("stadsdelen", stadsdeel)[1]) = 1]'>
                <xsl:sort select='stadsdeel' data-type='text' order="ascending"/>
            </xsl:apply-templates>
        </stadsdelen>
    </xsl:template>
    
    <xsl:template match='element'>
        <stadsdeel>
            <naam>
                <xsl:value-of select='stadsdeel'/>
            </naam>
        </stadsdeel>
    </xsl:template>
    
</xsl:stylesheet>
