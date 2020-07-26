#!/usr/bin/python
# -*- coding: utf-8 -*-
from keyids import KEYIDS

keyBindings = {}

def addKeyBinding(domain, key, context, action, flags):
	keyBindings.setdefault((context, action), []).append((key, domain, flags))

def removeKeyBinding(key, context, action, wild=True):
	if wild and action == "*":
		for ctx, action in keyBindings.keys():
			if ctx == context:
				removeKeyBinding(key, context, action, False)
		return
	contextAction = (context, action)
	if contextAction in keyBindings:
		bind = [x for x in keyBindings[contextAction] if x[0] != key]
		if bind:
			keyBindings[contextAction] = bind
		else:
			del keyBindings[contextAction]

# Returns a list of (key, flags) for a specified action.
#
def queryKeyBinding(context, action):
	if (context, action) in keyBindings:
		return [(x[0], x[2]) for x in keyBindings[(context, action)]]
	else:
		return []

def getKeyDescription(key):
	for key_name, key_id in KEYIDS.items():
		if key_id != key: continue
		if key_name.startswith("KEY_"):
			return (key_name[4:],)
		return

def getKeyBindingKeys(filterfn=lambda key: True):
	return filter(filterfn, keyBindings)

# Remove all entries of domain "domain".
#
def removeKeyBindings(domain):
	for x in keyBindings:
		keyBindings[x] = filter(lambda e: e[1] != domain, keyBindings[x])
