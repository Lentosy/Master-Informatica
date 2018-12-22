#!/bin/sh

/usr/local/glassfish4/bin/asadmin start-domain
/usr/local/glassfish4/bin/asadmin create-jdbc-connection-pool --datasourceclassname com.mysql.jdbc.jdbc2.optional.MysqlDataSource --restype javax.sql.DataSource --property portNumber=3306:password=test:user=groep20:serverName=groep20-DB:databaseName=PrisonersDilemma:relaxautocommit=true PersoonPool
/usr/local/glassfish4/bin/asadmin create-jdbc-resource --connectionpoolid PersoonPool jdbc/personen
/usr/local/glassfish4/bin/asadmin -u admin deploy --name Prisoners_Dilemma --contextroot /Prisoners_Dilemma /Prisoners_Dilemma.war
/usr/local/glassfish4/bin/asadmin stop-domain
/usr/local/glassfish4/bin/asadmin create-jvm-options -Dcom.sun.xml.ws.spi.db.BindingContextFactory=com.sun.xml.ws.db.toplink.JAXBContextFactory
/usr/local/glassfish4/bin/asadmin enable-secure-admin
/usr/local/glassfish4/bin/asadmin start-domain --verbose
