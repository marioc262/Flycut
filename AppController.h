//
//  AppController.m
//  Flycut
//
//  Flycut by Gennadiy Potapov and contributors. Based on Jumpcut by Steve Cook.
//  Copyright 2011 General Arcade. All rights reserved.
//
//  This code is open-source software subject to the MIT License; see the homepage
//  at <https://github.com/TermiT/Flycut> for details.
//

#import <Cocoa/Cocoa.h>
#import <ApplicationServices/ApplicationServices.h>
#import "BezelWindow.h"
#import "SRRecorderControl.h"
#import "SRKeyCodeTransformer.h"
#import "FlycutStore.h"
#import "SGHotKey.h"

@class SGHotKey;

@interface AppController : NSObject <NSMenuDelegate,NSTabViewDelegate> {
    BezelWindow					*bezel;
	SGHotKey					*mainHotKey;
	IBOutlet SRRecorderControl	*mainRecorder;
	IBOutlet NSPanel			*prefsPanel;
	IBOutlet NSBox              *appearancePanel;
    IBOutlet NSArrayController *ignoreListArrayController;
    BOOL                        isIgnoreListLoaded;
	int							mainHotkeyModifiers;
	SRKeyCodeTransformer        *srTransformer;
	BOOL						isBezelDisplayed;
	BOOL						isBezelPinned; // Currently not used
	NSString					*currentKeycodeCharacter;
    int							stackPosition;
    int							favoritesStackPosition;
    int							stashedStackPosition;
    NSDateFormatter*            dateFormat;
	
    FlycutStore				*clippingStore;
    FlycutStore				*favoritesStore;
    FlycutStore				*stashedStore;
    
    // Status item -- the little icon in the menu bar
    NSStatusItem *statusItem;
    NSString *statusItemText;
    NSImage *statusItemImage;
    
    // The menu attatched to same
    IBOutlet NSMenu *jcMenu;
    int jcMenuBaseItemsCount;
    IBOutlet NSSearchField *searchBox;
    NSResponder *menuFirstResponder;
    NSRunningApplication *currentRunningApplication;
    NSEvent *menuOpenEvent;
    IBOutlet NSSlider * heightSlider;
    IBOutlet NSSlider * widthSlider;
    // A timer which will let us check the pasteboard;
    // this should default to every .5 seconds but be user-configurable
    NSTimer *pollPBTimer;
    // We want an interface to the pasteboard
    NSPasteboard *jcPasteboard;
    // Track the clipboard count so we only act when its contents change
    NSNumber *pbCount;
    BOOL disableStore;
    //stores PasteboardCount for internal Flycut pasteboard actions so they don't trigger any events
    NSNumber *pbBlockCount;
    //Preferences
	NSDictionary *standardPreferences;
    int jcDisplayNum;
	BOOL issuedRememberResizeWarning;
}

// Basic functionality
-(void) pollPB:(NSTimer *)timer;
-(BOOL) addClipToPasteboardFromCount:(int)indexInt;
-(void) setPBBlockCount:(NSNumber *)newPBBlockCount;
-(void) hideApp;
-(void) pasteFromStack;
-(void) saveFromStack;
-(void) fakeCommandV;
-(void) stackUp;
-(void) stackDown;
-(IBAction)clearClippingList:(id)sender;
-(IBAction)mergeClippingList:(id)sender;
-(void)controlTextDidChange:(NSNotification *)aNotification;
-(BOOL)control:(NSControl *)control textView:(NSTextView *)fieldEditor doCommandBySelector:(SEL)commandSelector;
-(IBAction)searchItems:(id)sender;

// Stack related
-(BOOL) isValidClippingNumber:(NSNumber *)number;
-(NSString *) clippingStringWithCount:(int)count;
	// Save and load
-(void) saveEngine;
-(void) loadEngineFromPList;

// Hotkey related
-(void)hitMainHotKey:(SGHotKey *)hotKey;

// Bezel related
-(void) updateBezel;
-(void) showBezel;
-(void) hideBezel;
-(void) processBezelKeyDown:(NSEvent *)theEvent;
-(void) processBezelMouseEvents:(NSEvent *)theEvent;
-(void) metaKeysReleased;

// Menu related
-(void) updateMenu;
-(IBAction) processMenuClippingSelection:(id)sender;
-(IBAction) activateAndOrderFrontStandardAboutPanel:(id)sender;

// Preference related
-(IBAction) showPreferencePanel:(id)sender;
-(IBAction) setRememberNumPref:(id)sender;
-(IBAction) setFavoritesRememberNumPref:(id)sender;
-(IBAction) setDisplayNumPref:(id)sender;
-(IBAction) setBezelAlpha:(id)sender;
-(IBAction) setBezelHeight:(id)sender;
-(IBAction) setBezelWidth:(id)sender;
-(IBAction) switchMenuIcon:(id)sender;
-(IBAction) toggleLoadOnStartup:(id)sender;
-(IBAction) toggleMainHotKey:(id)sender;
-(void) setHotKeyPreferenceForRecorder:(SRRecorderControl *)aRecorder;

@end
