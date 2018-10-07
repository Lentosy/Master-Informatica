<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
    <xsl:output method="xml"/>
    
    
   
    <xsl:key name="straten-per-stadsdeel" match="element" use = "concat(stadsdeel, straatnaam)" /> 
    
    <xsl:template match="/root">
        <stadsdelen>
            
       
        <xsl:apply-templates select="element[generate-id() = generate-id(key('straten-per-stadsdeel',concat(stadsdeel, straatnaam))[1])]"/>
         </stadsdelen>
    </xsl:template>
    
    <xsl:template match="element">
        <xsl:variable name="element" select="key('straten-per-stadsdeel',concat(stadsdeel, straatnaam))"/>
        <stadsdeel>
            <naam>
                <xsl:value-of select="stadsdeel"/>
            </naam>
         
            <xsl:for-each select="$element">
                <straat>
                    <xsl:value-of select="straatnaam"/>
                </straat>
            </xsl:for-each>
        </stadsdeel>
        

    </xsl:template>
    

</xsl:stylesheet>


<!--
<page>
   <document>
      <id>1001</id>
      <cur>USD</cur>
      <date>01.01.2009</date>
      <amount>10</amount>
   </document>
   <document>
      <id>1001</id>
      <cur>USD</cur>
      <date>02.01.2009</date>
      <amount>15</amount>
   </document>
 </page>


<?xml version='1.0'?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:key name="idcur" match="document" use="concat(id,cur)"/>

<xsl:template match="/page">
    <xsl:apply-templates select="document[generate-id() = generate-id(key('idcur',concat(id,cur))[1])]"/>
</xsl:template>

<xsl:template match="document">
<xsl:variable name="document" select="key('idcur',concat(id,cur))"/>
Bill: id=<xsl:value-of select="id"/>, cur=<xsl:value-of select="cur"/>
    <xsl:for-each select="$document">
      date=<xsl:value-of select="date"/>   amount=<xsl:value-of select="amount"/>
    </xsl:for-each>
      total amount=<xsl:value-of select="sum($document/amount)"/>
</xsl:template>
</xsl:stylesheet>-->