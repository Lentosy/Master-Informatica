package auctionserver.model;

/**
 *
 * @author vongenae
 */
public class Item {
    private final int id;
    private final double minPrice;
    private final String description;

    public Item(int id, String description, double minPrice) {
        this.id = id;
        this.description = description;
        this.minPrice = minPrice;
    }

    public int getId() {
        return id;
    }

    public String getDescription() {
        return description;
    }

    public double getMinPrice() {
        return minPrice;
    }

}
