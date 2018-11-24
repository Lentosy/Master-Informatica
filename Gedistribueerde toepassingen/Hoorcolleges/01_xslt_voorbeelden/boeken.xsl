<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" 
                xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="html"/>
    <xsl:template match="/">
        <html>
            <head>
                <link rel="stylesheet" type="text/css" 
                              href="boekenxsl.css"/>
                <title>Overzicht boeken</title>
            </head>
            <body>
                <h1>Overzicht boeken</h1>
                <xsl:text>Er zijn </xsl:text>
                <xsl:value-of select="count(books/book)"/> 
                <xsl:text> boeken in de catalogus.</xsl:text>
                <xsl:apply-templates/>
            </body>
        </html>
    </xsl:template>

    <xsl:template match="books">
        <ul>
            <xsl:apply-templates/>
        </ul>
    </xsl:template>

    <xsl:template match="book">
        <li>
            <xsl:apply-templates select="title"/>
            <xsl:text>, </xsl:text>
            <xsl:for-each select="author">
                <xsl:apply-templates select="."/>
                <xsl:text>, </xsl:text>
            </xsl:for-each>
            <xsl:apply-templates select="isbn"/>
        </li>
    </xsl:template>

    <xsl:template match="isbn">
        <i>ISBN</i>
        <xsl:text> </xsl:text>
        <xsl:value-of select="."/>
    </xsl:template>

    <xsl:template match="title">
        <i>
            <xsl:value-of select="."/>
        </i>
    </xsl:template>

    <xsl:template match="author">
        <xsl:for-each select="firstname">
            <xsl:apply-templates select="."/>
            <xsl:text> </xsl:text>
        </xsl:for-each>
        <xsl:apply-templates select="initial" />
        <xsl:text> </xsl:text>
        <xsl:apply-templates select="name" />
    </xsl:template>

</xsl:stylesheet>