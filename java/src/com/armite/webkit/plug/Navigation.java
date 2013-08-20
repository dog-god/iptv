package com.armite.webkit.plug;

public class Navigation {
	public Object curElement = null;
	  public boolean isDefaultNavigation = false;
	  public boolean isHighlight = true;

	  public void disableDefaultNavigation()
	  {
	    this.isDefaultNavigation = false;
	    //i.b("Navigation", "disableDefaultNavigation()");
	  }

	  public void disableHighlight()
	  {
	    this.isHighlight = false;
	   // i.b("Navigation", "disableHighlight()");
	  }

	  public void enableDefaultNavigation()
	  {
	    this.isDefaultNavigation = true;
	  //  i.b("Navigation", "enableDefaultNavigation()");
	  }

	  public void enableHighlight()
	  {
	    this.isHighlight = true;
	    //i.b("Navigation", "enableHighlight()");
	  }

	  public int focusElement(Object paramObject)
	  {
	    this.curElement = paramObject;
	    //i.b("Navigation", "focusElement() obj:" + paramObject);
	    return 0;
	  }

	  public Object getCurrentElement()
	  {
	    //if (i.a)
	     // i.b("Navigation", "getCurrentElement()" + this.curElement);
	    return this.curElement;
	  }

	  public boolean getDefaultNavigation()
	  {
	    //if (i.a)
	   //   i.b("Navigation", "getDefaultNavigation:" + this.isDefaultNavigation);
	    return this.isDefaultNavigation;
	  }

	  public boolean getHighlight()
	  {
	   // if (i.a)
	   //   i.b("Navigation", "getHighlight:" + this.isHighlight);
	    return this.isHighlight;
	  }
}
