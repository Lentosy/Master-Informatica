package GrafischeTechnieken;

import java.awt.geom.*;
import javax.swing.*;

public interface AssenStelselListener {
    public void assenStelselChanged(double xMin, double yMin, double xMax, double yMax);

    public void setAssenStelselMark(Rectangle2D r);

    public void recenter(double x, double y);

    public double getWidthOnScreen();

    public double getHeightOnScreen();

    public JComponent getAsComponent();

    public void defaultView();

    public void fitToScreen();
}
