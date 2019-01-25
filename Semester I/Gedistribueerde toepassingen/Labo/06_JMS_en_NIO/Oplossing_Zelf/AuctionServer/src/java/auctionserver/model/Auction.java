package auctionserver.model;

import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.sql.rowset.CachedRowSet;
import javax.sql.rowset.RowSetFactory;
import javax.sql.rowset.RowSetProvider;

/**
 *
 * @author vongenae
 */
public class Auction {
    List<Item> items;
    Map<Integer,Item> allItems;
    Random r;

    public Auction() {
        items = new ArrayList<>();
        allItems = new HashMap<>();
        r = new Random();
        try {
            RowSetFactory myRowSetFactory = RowSetProvider.newFactory();
            CachedRowSet auctionRS = myRowSetFactory.createCachedRowSet();

            auctionRS.setDataSourceName("jdbc/auction");

            auctionRS.setCommand("select id, description, minprice from auction");
            auctionRS.execute();
            while (auctionRS.next()) {
                Item item = new Item(auctionRS.getInt(1), auctionRS.getString(2), auctionRS.getDouble(3));
                items.add(item);
                allItems.put(item.getId(), item);
            }
            Logger.getLogger(Auction.class.getName()).log(Level.INFO, "aantal items: {0}", items.size());
        } catch (SQLException ex) {
            Logger.getLogger(Auction.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public Item getItem() {
        Item item = null;
        if (items.size() > 0) {
            int index = r.nextInt(items.size());
            item = items.remove(index);
        }
        return item;
    }
}
