<?xml version="1.0"?>

<!-- Question 7 b -->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

    <xsl:output method="html" doctype-system="about:legacy-compat"/>
    <xsl:template match="/">

    <html xmlns="http://www.w3.org/1999/xhtml">
        <head>
            <meta charset="utf-8"></meta>
            <title>Question 7b</title>
        </head>
        <body>
            <table border="2">
                <caption>Nutrition Facts</caption>
                <thead>
                    <tr>
                        <th>Product Name</th>
                        <th>Serving Size</th>
                        <th>Calories</th>
                        <th>Fat Calories</th>
                        <th>Fat</th>
                        <th>Saturated Fat</th>
                        <th>Cholesterol</th>
                        <th>Sodium</th>
                        <th>Total Carbohydrates</th>
                        <th>Fiber</th>
                        <th>Sugars</th>
                        <th>Protein</th>
                    </tr>
                </thead>
                <xsl:for-each select="/nutrition_facts">
                    <td><xsl:value-of select="product_name"></xsl:value-of></td>
                    <td><xsl:value-of select="serving_size"></xsl:value-of></td>
                    <td><xsl:value-of select="calories"></xsl:value-of></td>
                    <td><xsl:value-of select="fat_calories"></xsl:value-of></td>
                    <td><xsl:value-of select="fat"></xsl:value-of></td>
                    <td><xsl:value-of select="saturated_fat"></xsl:value-of></td>
                    <td><xsl:value-of select="cholesterol"></xsl:value-of></td>
                    <td><xsl:value-of select="sodium"></xsl:value-of></td>
                    <td><xsl:value-of select="total_carbohydrates"></xsl:value-of></td>
                    <td><xsl:value-of select="fiber"></xsl:value-of></td>
                    <td><xsl:value-of select="sugars"></xsl:value-of></td>
                    <td><xsl:value-of select="protein"></xsl:value-of></td>
                </xsl:for-each>
            </table>
        </body>
    </html>
    </xsl:template>
</xsl:stylesheet>