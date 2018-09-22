<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>
    <xsl:template match="/">
        <html>
            <head>
                <title>Overzicht foto's</title>
            </head>
            <body>
                <h1>Overzicht foto's</h1>
                <xsl:apply-templates select="servers/server"/>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="server">
        <xsl:variable name="urlhost" select="url"/>
        <table border="1">
            <tr>
                <th colspan="2">
                    <xsl:value-of select="$urlhost"/>
                </th>
            </tr>
            <xsl:apply-templates select="foto">
                <xsl:with-param name="host" 
                                select="$urlhost"/>
            </xsl:apply-templates>
        </table> 
        <br></br>
    </xsl:template>

    <xsl:template match="foto">
        <xsl:param name="host"/>
        <xsl:variable name="urlFoto">
            <xsl:value-of select="$host"/>
            <xsl:text>/</xsl:text>
            <xsl:value-of select="@bron"/>
        </xsl:variable>
        <tr>
            <td>
                <a>
                    <xsl:attribute name="href">
                        <xsl:value-of select="$urlFoto"/>
                    </xsl:attribute>
                    <xsl:value-of select="."/>
                </a>
            </td>
            <td>
                <xsl:value-of select="$urlFoto"/>
            </td>
        </tr>
    </xsl:template>
</xsl:stylesheet>

