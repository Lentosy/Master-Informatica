/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package restservice;


import com.google.gson.Gson;
import groep20.models.Game;
import groep20.persistence.DatabaseWrapper;
import java.sql.SQLException;
import java.util.List;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.ejb.Stateless;
import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.PathParam;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

/**
 *
 * @author thomas
 */
@Stateless
@Path("/")
public class PDWebService {

   private final DatabaseWrapper db;
   private final Gson gson;
    
    public PDWebService() {
        db = new DatabaseWrapper();
        gson = new Gson();
        
    }

    // current url: http://localhost:8080/Prisoners_Dilemma/games
    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response findAll() {
        try {
            return Response.status(200).entity(gson.toJson(db.getAllGames())).build();
        } catch (SQLException ex) {
            Logger.getLogger(PDWebService.class.getName()).log(Level.SEVERE, null, ex);
        }
       return null;
   
    }
    
    //http://localhost:8080/Prisoners_Dilemma/games/naam_van_speler
   
    @GET
    @Path("{player}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response find(@PathParam("player") String playerName) {
        try {
            return Response.status(200).entity(gson.toJson(db.getGamesForPlayer(playerName))).build();
        } catch (SQLException ex) {
            Logger.getLogger(PDWebService.class.getName()).log(Level.SEVERE, null, ex);
        }
       return null;
   
    }

}