class PM_GroupContextMenu extends ScriptedWidgetEventHandler
{
    private Widget                                      m_group_context_menu_root_widget;
    protected ref array<ref PM_UI_Category>             m_options;
    protected ref PM_UI_Category                        m_option_displayed;

    void PM_GroupContextMenu()
    {
        m_options = new array<ref PM_UI_Category>;
        Init();
    }

    /*--------------------------------------------------------------------------
        Note:
            If you want to make any changes to the layout, changes should be made here.
            For further modification of the UI, I highly recommend that you redo a class based on it.
    */
    void Init()
	{
        m_group_context_menu_root_widget = GetGame().GetWorkspace().CreateWidgets("partyme/gui/layouts/group.layout");
        m_group_context_menu_root_widget.SetHandler(this);
        AddCategories();
    }

    void AddCategories()
    {
        m_options.Insert(new PM_UI_Option_Party(m_group_context_menu_root_widget, m_options.Count()));
    }

    Widget GetMainWidget()
    {
        return m_group_context_menu_root_widget;
    }

    //--------------------------------------------------------------------------
    void Show(int x, int y)
    {
        m_group_context_menu_root_widget.SetPos(x, y);
        m_group_context_menu_root_widget.Show(true);
    }

    void Hide()
    {
        m_group_context_menu_root_widget.Show(false);
    }

    bool IsVisible()
	{
		return m_group_context_menu_root_widget.IsVisible();
	}

    /*--------------------------------------------------------------------------
        Events
    */
   override bool OnClick(Widget w, int x, int y, int button)
   {
       foreach (ref PM_UI_Category option : m_options)
       {
           if (option.OnClick(w, x, y, button))
           {
               return true;
           }
       }
       if (m_option_displayed.OnClick(w, x, y, button))
       {
           return true;
       }
       return super.OnClick(w, x, y, button);
   }

   override bool OnMouseEnter(Widget w, int x, int y)
   {
       foreach (ref PM_UI_Category option : m_options)
       {
           if (option.OnMouseEnter(w, x, y))
           {
               return true;
           }
       }
       if (m_option_displayed.OnMouseEnter(w, x, y))
       {
           return true;
       }
       return super.OnMouseEnter(w, x, y);
   }

   override bool OnMouseLeave(Widget w, Widget enterW, int x, int y)
   {
       foreach (ref PM_UI_Category option : m_options)
       {
           if (option.OnMouseLeave(w, enterW, x, y))
           {
               return true;
           }
       }
       if (m_option_displayed.OnMouseLeave(w, enterW, x, y))
       {
           return true;
       }
       return super.OnMouseLeave(w, enterW, x, y);
   }

   override bool OnDrag(Widget w, int x, int y)
   {
       foreach (ref PM_UI_Category option : m_options)
       {
           if (option.OnDrag(w, x, y))
           {
               return true;
           }
       }
       if (m_option_displayed.OnDrag(w, x, y))
       {
           return true;
       }
       return super.OnDrag(w, x, y);
   }

   override bool OnDrop(Widget w, int x, int y, Widget reciever)
   {
       foreach (ref PM_UI_Category option : m_options)
       {
           if (option.OnDrop(w, x, y, reciever))
           {
               return true;
           }
       }
       if (m_option_displayed.OnDrop(w, x, y, reciever))
       {
           return true;
       }
       return super.OnDrop(w, x, y, reciever);
   }

   void Update(float timeslice)
   {
       foreach (ref PM_UI_Category option : m_options)
       {
           option.Update(timeslice);
       }
   }
};